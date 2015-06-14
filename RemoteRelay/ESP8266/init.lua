if true then
	wifi.setmode(wifi.STATION)
	wifi.sta.config("laker","leafnethereur")
	wifi.sta.connect()
	cnt = 0
	tmr.alarm(1, 1000, 1, function() 
	    if (wifi.sta.getip() == nil) and (cnt < 20) then 
	    	print("IP unavaiable, Waiting...")
	    	cnt = cnt + 1 
	    else 
	    	tmr.stop(1)
	    	if (cnt < 20) then 
                               print("Config done, Host IP="..wifi.sta.getip())
	    	     dofile("mqtt.lua")                           
	    	else 
                               node.restart()
	    	end
	    end 
	 end)
end