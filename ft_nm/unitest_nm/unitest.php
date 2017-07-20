#!/usr/bin/php
<?php
    define ("NAME_FILE", "list_bin_test");
    // test 64bits -j -n -u -p -U -r -A -g -o ok
    // test 32bits -j -n -u -p -U -r -A -g -o ok
        //warning -A et -o ne vont pas ensemble
    //gestion des .o

    $file_content = file_get_contents(NAME_FILE);
    $array_bin = explode("\n", $file_content);
    $count = 0;
    $valide_bin = 0;
    $error = "";
    $flags = $argc > 1 ? $argv[1] : "";
    $bin_prev = "";

    if (file_exists("../ft_nm") == false)
    {
        echo "../ft_nm is missing\n";
        exit(-1);
    }

    foreach ($array_bin as $bin)
        if (isset($bin) && !empty($bin))
        {
            //echo  "./../ft_nm ".$flags." ".$bin." ".$bin_prev."\n";
            $count++;
            $rep_nm = shell_exec("nm ".$flags." ".$bin." ".$bin_prev);
            $rep_ft_nm = shell_exec("./../ft_nm ".$flags." ".$bin." ".$bin_prev);
            if ($rep_ft_nm != $rep_nm)
            {
                echo "Difference Bin : " . $bin . "\n";
                $error = "nm ".$flags." ".$bin." ".$bin_prev." > base && ./../ft_nm ".$flags." ".$bin." ".$bin_prev." > test && diff base test";
            }
            else
            {
                //$bin_prev = $bin;
                $valide_bin++;
            }
        }
    echo $count." / ".$valide_bin." ok avec option(s) : ".$flags."\n";
    if (isset($error) && !empty($error))
        echo shell_exec($error);
?>