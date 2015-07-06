<?php
	$serverResponse = exec('(cd /home/pi/Desktop/GV_PLC_interface && ./gv webfetch)');
	if ($serverResponse != "SUCCESS") {
		echo "Unable to fetch data.";
	} else {
		echo "<pre>";
		$data = file_get_contents('webready.json', FILE_USE_INCLUDE_PATH);
		var_dump($data);
		echo "</pre>";
	}




?>
