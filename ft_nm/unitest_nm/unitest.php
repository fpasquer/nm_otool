#!/usr/bin/php
<?php
    define ("NAME_FILE", "list_bin_test");
    // test 64bits -j -n -u -p -U -r -A ok
    // test 32bits -j -n -u -p -U -r -A ok
    //gestion des .o

    $file_content = file_get_contents(NAME_FILE);
    $array_bin = explode("\n", $file_content);
    $count = 0;
    $valide_bin = 0;
    $error = "";
    $flags = $argc > 1 ? $argv[1] : "";
    if (file_exists("../ft_nm") == false)
    {
        echo "../ft_nm is missing\n";
        exit(-1);
    }
    foreach ($array_bin as $bin)
        if (isset($bin) && !empty($bin))
        {
            $count++;
            $rep_nm = shell_exec("nm ".$flags." ".$bin);
            $rep_ft_nm = shell_exec("./../ft_nm ".$flags." ".$bin);
            if ($rep_ft_nm != $rep_nm)
            {
                echo "Difference Bin : " . $bin . "\n";
                $error = "nm ".$flags." ".$bin." > base && ./../ft_nm ".$flags." ".$bin." > test && diff base test";
            }
            else
                $valide_bin++;
        }
    echo $count." / ".$valide_bin." ok\n";
    if (isset($error) && !empty($error))
        echo shell_exec($error);
?>