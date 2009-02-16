<?php

$file = "../VERSION";

$raw_version = file_get_contents($file);
$numbers = array();
if (preg_match("#^(\d+).(\d+).(\d+).(\d+)#", $raw_version, $numbers) == 1 && count($numbers) == 5)
{
   $new_raw_version = $numbers[1] . "." . $numbers[2] . "." . (++$numbers[3]) . "." . time();
   file_put_contents($file, $new_raw_version);
}
else
{
   throw new Exception("Invalid version number: " . $raw_version);
}


