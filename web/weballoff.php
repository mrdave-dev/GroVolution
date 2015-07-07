<?php
	$serverResponse = exec('(cd /home/pi/Desktop/GV_PLC_interface && ./gv weballoff)');
	if ($serverResponse != "SUCCESS") {
		echo "Unable to fetch data.";
	}




?>
