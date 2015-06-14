did = "/1"
DIDACK=false
function connect(m)
m:connect("cyberrelay.cloudapp.net", 1883, 0, 
function(conn) 
    print("connected") 
    m:subscribe("smartrelay" .. did,2, function(conn) print("subscribe success") end)
    tmr.alarm(0, 5000, 1, function()
        if (DIDACK == false) then
          print("<DID>" .. did .. "</DID>")          
        else 
          if (node.heap() < 6144) then 
            print("low mem, restart")
            print("<MQTT>smartrelay" .. did .. ":reset</MQTT>")
            node.restart()
          end
        end        
    end)
end)
end

m = mqtt.Client("smartrelay" .. did, 120, "u", "p")
m:on("connect", function(con) print ("connected") end)
m:on("offline", function(con) 
  print("<MQTT>smartrelay" .. did .. ":reset</MQTT>")
  node.restart()
end)
m:on("message", function(conn, topic, data)
  if data ~= nil then
    print("<MQTT>" .. topic .. ":" .. data .. "</MQTT>")
  else
    print("<MQTT>" .. topic .. "</MQTT>")
  end
end)

connect(m)



