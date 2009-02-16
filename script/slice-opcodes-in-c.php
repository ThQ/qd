#!/bin/php
<?php

function rfill_string($s, $len, $c)
{
   while (strlen($s) < $len)
   {
      $s = $c . $s;
   }
   return $s;
}

function fill_string($s, $len, $c)
{
   while(strlen($s) < $len)
   {
      $s .= $c;
   }
   return $s;
}

$source_file = "../include/svm/OpCode.h";
$opcodes = parse_ini_file("../data/opcodes.ini", false);
ksort($opcodes);
print_r($opcodes);
$c = file_get_contents($source_file);

$c_s = substr($c, 0, strpos($c, "// [opcodes]"));
$c_e = substr($c, strpos($c, "// [/opcodes]", $c_s));

$c_final =  $c_s . "// [opcodes]\n";
foreach ($opcodes as $name => $value)
{
   $c_final .= fill_string("#define OPC_" . $name, 40, " ") . " ";
   $c_final .= rfill_string(ord($value), 5, " ") . "    /*   " . $value . "   */\n";
}
$c_final .= $c_e;

echo $c_final;

file_put_contents($source_file, $c_final);
file_put_contents("../build/opcodes-spliced", " ");
