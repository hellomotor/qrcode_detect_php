<?php
include "qrcode_detect.php";
if ($argc == 2) {
	$filename = $argv[1];
	from_file($filename);
	//from_memory($filename);
}

function from_file($filename)
{
	$error = 0;
	$result = qrcode_detect::single_detect_file($filename, &$error);
	if (!$result)
		fprintf(STDERR, "Detect from file failed, error code %d\n", $error);
	else 
		fprintf(STDOUT, "%s\n", $result);
}

function from_memory($filename)
{
	$error = 0;
	$image = file_get_contents($filename);
	$image_png = 0; #"PNG"
	$image_jpg = 1; #"JPG"
	$result = qrcode_detect::single_detect_memory($image, strlen($image), $image_png, &$error);
	if (!$result)
		printf("Detect from memory failed, error code %d\n", $error);
	else 
		echo $result."\n";
}
?>
