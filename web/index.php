<?php 
echo "<pre>";
   echo exec('(cd /home/pi/Desktop/GV_PLC_interface && ./gv fetch)'); 

   $data = file_get_contents('webready.json', FILE_USE_INCLUDE_PATH);

   var_dump($data);
echo "</pre>";
?>

