<?php
	$serverResponse = exec('(cd /home/pi/Desktop/GV_PLC_interface && ./gv weballon)');
	if ($serverResponse != "SUCCESS") {
		echo "Unable to fetch data.";
	}




?>
