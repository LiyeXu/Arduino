using System;
using System.Diagnostics;
using System.Net;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace AcService.UnitTest
{
    [TestClass]
    public class MqttClientTest
    {
        [TestMethod]
        public void SubscriptionTest()
        {
            ManualResetEvent waitable = new ManualResetEvent(false);
            var host = Dns.Resolve("cyberrelay.cloudapp.net");
            Assert.IsTrue(host.AddressList.Length != 0);
            var ip = host.AddressList[0];
            Debug.WriteLine(ip.ToString());
            MqttClient client = new MqttClient(ip);
            client.MqttMsgPublishReceived += (sender, e) => {
                var data = Encoding.UTF8.GetString(e.Message);
                var s = new JavaScriptSerializer();
                var obj = s.Deserialize<Payload>(data);
                Debug.WriteLine("Temp:{0}", obj.temperature);
                waitable.Set();
            };
            string clientId = Guid.NewGuid().ToString();
            client.Connect(clientId);
            Assert.IsTrue(client.IsConnected);
            Debug.WriteLine("connected to broker.");
            client.Subscribe(new string[] { "smartrelay/2/sensors" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
            Debug.WriteLine("subscribed to topic.");
            bool received = WaitHandle.WaitAll(new[] { waitable }, 5 * 60 * 1000);
            Assert.IsTrue(received);
        }

        [TestMethod]
        public void PublishingTest()
        {
            var host = Dns.Resolve("cyberrelay.cloudapp.net");
            Assert.IsTrue(host.AddressList.Length != 0);
            var ip = host.AddressList[0];
            Debug.WriteLine(ip.ToString());
            MqttClient client = new MqttClient(ip); 
            string clientId = Guid.NewGuid().ToString();
            client.Connect(clientId);
            Assert.IsTrue(client.IsConnected);
            Debug.WriteLine("connected to broker.");
            client.Publish("smartrelay/2", Encoding.UTF8.GetBytes("ir:send1"));
            Debug.WriteLine("published to topic.");
        }
    }
}
