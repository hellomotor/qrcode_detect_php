<?php
include "qrcode_detect.php";
#$imageDir = "/root/zxing-2.2/cpp/php/images";
#$imagePattern = sprintf("%s/*.png", $imageDir);
if ($argc == 2) {
	foreach (glob($argv[1]) as $filename) {
		echo $filename."\t=>\t";
		if (is_file($filename))  {
			echo qrcode_detect::single_detect($filename)."\n";
		}
	}
}
?>
