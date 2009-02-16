<?php

$FILES = array();
$FILES["c++"] = "test-cpp";
$FILES["c#"] = "test.exe";
$FILES["java"] = "Test.class";
$FILES["php"] = "test.php";
$FILES["python"] = "test.py";
$FILES["ruby"] = "test.rb";
$FILES["parrot"] = "test.pasm";
$FILES["perl"] = "test.pl";
$FILES["svm"] = "test.sop";

$RUNNERS = array();
$RUNNERS["c++"] = "./\${file}";
$RUNNERS["c#"] = "mono \${file}";
$RUNNERS["java"] = "java \${file.base}";
$RUNNERS["parrot"] = "parrot \${file}";
$RUNNERS["php"] = "php \${file}";
$RUNNERS["python"] = "python \${file}";
$RUNNERS["ruby"] = "ruby \${file}";
$RUNNERS["perl"] = "perl \${file}";
$RUNNERS["svm"] = "svm \${file}";

if ($argc > 2)
{
      # $argv[0] : test folder
      # $argv[1] : language list

      if (is_dir($argv[1]))
      {
         chdir($argv[1]);
         $cmd_tests = split(",", $argv[2]);
         if ($argv[2] == "_")
         {
            $cmd_tests = array_keys($FILES);
         }
         $results = array();
         $runners = array();


         foreach ($cmd_tests as $test_name)
         {
            if (isset($FILES[$test_name]))
            {
               if (file_exists($FILES[$test_name]))
               {
                  $pathinfo = pathinfo($FILES[$test_name]);
                  $runners[$test_name] = $RUNNERS[$test_name];
                  $runners[$test_name] = str_replace("\${file}", $pathinfo["basename"], $runners[$test_name]);
                  $runners[$test_name] = str_replace("\${file.base}", $pathinfo["filename"], $runners[$test_name]);
                  $results[$test_name] = 0;
               }
               else
               {
                  echo "Cannot find test file [" . $argv[1] . "/" . $FILES[$test_name] . "].\n";
               }
            }
            else
            {
               echo "Cannot find test language [" . $test_name . "].";
            }
         }

         foreach ($runners as $test => $runner)
         {
            $output = array();
            $errno = 0;
            $last_line = "";

            $start = microtime(true);
            $last_line = exec($runner, $output, $errno);
            $end = microtime(true);
            $results[$test] = array();
            $results[$test]["time"] = $end - $start;
            $results[$test]["errno"] = $errno;
            $results[$test]["lines"] = count($output);
            $results[$test]["last_line"] = $last_line;
         }

         ksort($results);
         $total = 0;
         $lowest_time = min(array_values($results));
         echo "\nResults (" . $argv[1] . ")\n";
         echo str_repeat("-", 80) . "\n";
         foreach ($results as $test => $result)
         {
            $test_language = str_pad("" . $test, 10, " ", STR_PAD_LEFT);
            
            echo  $test_language . ": ";

            if ($result["errno"] == 0)
            {
               echo $result["time"] . "s \n";
               $total += $result["time"];
            }
            else
            {
               echo "FAILED (with error " . $result["errno"] . "). Last line was : \"" . $result["last_line"] . "\".\n";
            }
            
         }
         echo str_repeat("-", 80) . "\n";
         echo str_pad("Total:", 10, " ", STR_PAD_LEFT) . " " . $total . "s \n";
      }
      else
      {
         echo $argv[1] . " is not a valid directory.";
      }

      /*
      $ext = pathinfo($argv[1], PATHINFO_EXTENSION);
      $start = microtime(true);

      if (isset($runners[$ext]))
      {
         $out = shell_exec($runners[$ext] . " " . $argv[1]);
       }
      else
      {
         $out = shell_exec($argv[1]);
      }
      $end = microtime(true);
      echo "\nTime spent : " . ($end - $start) . "\n";
      */
    
   
}
else
{
   echo "Bad argument count.\n";
}
