if true then
 ssidError = false;
 if (file.open("ssiderror", r) ~= nil) then
    ssidError = true;
    file.close()
 end 
 ssidFile = file.open("ssid", r)
 if (ssidFile == nil) or (ssidError == true) then
   print("No ssid, setup AP...")   
   if (ssidError == false) then
       wifi.setmode(wifi.SOFTAP)
   else
       wifi.setmode(wifi.STATIONAP)
   end
   cfg={}
   cfg.ssid= "CyberRelay_" .. node.chipid()
   cfg.pwd=nil
   wifi.ap.config(cfg)
   print("AP setup done! IP:" .. wifi.ap.getip())
   svr = net.createServer(net.TCP, 3600)
   svr:listen(80,function(c)
      print("Client app connected to port 80.")
      c:on("receive", function(sck, pl)
        print("Get ssid:" .. pl) 
        file.open("ssid", "w+")
        pair=string.gsub(pl, "@pwd@", "\n")
        file.writeline(pair)
        file.close()        
        print("ssid saved.")
        c:send("ACK")
        svr:close()
        node.restart()
      end)
   end)   
 end
 if (ssidFile ~= nil) then
     ssid = string.gsub(file.readline(), "\n", "")
     pwd = string.gsub(file.readline(), "\n", "")
     file.close()
 if (ssidError == false) then 
   wifi.setmode(wifi.STATION)
 end
 wifi.sta.config(ssid,pwd)
 wifi.sta.connect()
 cnt = 0
 tmr.alarm(1, 3000, 1, function() 
     if (wifi.sta.getip() == nil) and ((cnt < 20) or (ssidError == true)) then 
      print("IP unavaiable, Waiting...")
      cnt = cnt + 1 
     else 
      tmr.stop(1)
      if (wifi.sta.getip() ~= nil) then 
           if (ssidError) then
               file.remove("ssiderror")
               node.restart()
           else
                print("Config done, IP="..wifi.sta.getip())
                dofile("mqtt.lua")                           
           end
      else
           if (file.open("ssiderror", r) == nil) then
               file.open("ssiderror", "w+")
           end
           file.close()            
           node.restart()
      end
     end 
  end)
end
end