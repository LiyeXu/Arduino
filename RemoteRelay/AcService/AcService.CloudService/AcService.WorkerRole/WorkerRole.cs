using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using Microsoft.WindowsAzure;
using Microsoft.WindowsAzure.Diagnostics;
using Microsoft.WindowsAzure.ServiceRuntime;
using Microsoft.WindowsAzure.Storage;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace AcService.WorkerRole
{
    public class WorkerRole : RoleEntryPoint
    {
        private readonly CancellationTokenSource cancellationTokenSource = new CancellationTokenSource();
        private readonly ManualResetEvent runCompleteEvent = new ManualResetEvent(false);

        public override void Run()
        {
            Trace.TraceInformation("AcService.WorkerRole is running");

            try
            {
                this.RunAsync(this.cancellationTokenSource.Token).Wait();
            }
            finally
            {
                this.runCompleteEvent.Set();
            }
        }
        
        public override bool OnStart()
        {
            Microsoft.ApplicationInsights.Extensibility.TelemetryConfiguration.Active.InstrumentationKey = "3e9def73-97d2-4041-946f-012c5fdb3063";
            // Set the maximum number of concurrent connections
            ServicePointManager.DefaultConnectionLimit = 12;

            // For information on handling configuration changes
            // see the MSDN topic at http://go.microsoft.com/fwlink/?LinkId=166357.

            bool result = base.OnStart();

            Trace.TraceInformation("AcService.WorkerRole has been started");

            var host = Dns.Resolve("cyberrelay.cloudapp.net");
            var ip = host.AddressList[0];
            Trace.TraceInformation(ip.ToString());
            MqttClient client = new MqttClient(ip);
            client.MqttMsgPublishReceived += (sender, e) =>
            {
                DateTime now = TimeZoneInfo.ConvertTimeFromUtc
                    (DateTime.UtcNow, TimeZoneInfo.FindSystemTimeZoneById("China Standard Time"));
                if (now.Hour < Convert.ToInt32(RoleEnvironment.GetConfigurationSettingValue("WorkingBegin")) ||
                    now.Hour >= Convert.ToInt32(RoleEnvironment.GetConfigurationSettingValue("WorkingEnd")))
                {
                    Trace.TraceInformation("Off Duty!");
                    return;
                }
                var data = Encoding.UTF8.GetString(e.Message);
                var s = new JavaScriptSerializer();
                var obj = s.Deserialize<Payload>(data);
                if (now.Month >= 6 && now.Month <= 9 && obj.temperature >
                    Convert.ToInt32(RoleEnvironment.GetConfigurationSettingValue("TurnOnCoolAbove")))
                {
                    client.Publish("smartrelay/2", Encoding.UTF8.GetBytes("ir:send1"));
                    Trace.TraceInformation("Last action: Cooler On");
                }
                else if (now.Month >= 6 && now.Month <= 9 && obj.temperature <
                    Convert.ToInt32(RoleEnvironment.GetConfigurationSettingValue("TurnOffCoolBelow")))
                {
                    client.Publish("smartrelay/2", Encoding.UTF8.GetBytes("ir:send2"));
                    Trace.TraceInformation("Last action: Cooler Off");
                }
                else if ((now.Month >= 11 || now.Month <= 2) && obj.temperature <
                    Convert.ToInt32(RoleEnvironment.GetConfigurationSettingValue("TurnOnWarmBelow")))
                {
                    client.Publish("smartrelay/2", Encoding.UTF8.GetBytes("ir:send3"));
                    Trace.TraceInformation("Last action: Heat On");
                }
                else if ((now.Month >= 11 || now.Month <= 2) && obj.temperature >
                    Convert.ToInt32(RoleEnvironment.GetConfigurationSettingValue("TurnOffWarmAbove")))
                {
                    client.Publish("smartrelay/2", Encoding.UTF8.GetBytes("ir:send4"));
                    Trace.TraceInformation("Last action: Heat Off");
                }
                Trace.TraceInformation("Last temperature: {0}", obj.temperature);
            };
            string clientId = Guid.NewGuid().ToString();
            client.Connect(clientId);
            Trace.TraceInformation("connected to broker.");
            client.Subscribe(
                new string[] { "smartrelay/2/sensors" }, 
                new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
            Trace.TraceInformation("subscribed to topic.");

            return result;
        }

        public override void OnStop()
        {
            Trace.TraceInformation("AcService.WorkerRole is stopping");

            this.cancellationTokenSource.Cancel();
            this.runCompleteEvent.WaitOne();

            base.OnStop();

            Trace.TraceInformation("AcService.WorkerRole has stopped");
        }

        private async Task RunAsync(CancellationToken cancellationToken)
        {
            while (!cancellationToken.IsCancellationRequested)
            {
                await Task.Delay(60000);
            }
        }
    }
}
