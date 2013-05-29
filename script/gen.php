<?php

#wget -O --no-check-certificate 

function requestQrcode($text) {
	$url = 'https://chart.googleapis.com/chart?cht=qr&chs=220x220&choe=UTF-8&chld=L|2&chl='.$text;
	$ch = curl_init($url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);  
	if (!empty($headers)) 
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($ch, CURLOPT_POST, false);
	curl_setopt($ch, CURLOPT_VERBOSE, false);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
	$resp = curl_exec($ch); 
	$httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
	curl_close($ch);
	return $resp;
}

$fh = fopen("test_images/yoka.png", "w+");
$imageData = requestQrcode("http://at.yoka.com");
fwrite($fh, $imageData);
fclose($fh);

?>
