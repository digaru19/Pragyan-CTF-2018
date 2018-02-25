<?php

$sayings = array();

array_push($sayings, 
    "To err is human... to really screw up requires the root password.",
    "Life would be so much easier if we only had the source code.", 
    "My software never has bugs. It just develops random features.", 
    "The only problem with troubleshooting is that sometimes trouble shoots back.", 
    "If brute force doesn't solve your problems, then you aren't using enough.", 
    "Difference between a virus and windows ? Viruses rarely fail." , 
    "Most hackers are young because young people tend to be adaptable. As long as you remain adaptable, you can always be a good hacker.", 
    "There are only two kinds of languages: the ones people complain about and the ones nobody uses.", 
    "Perl - The only language that looks the same before and after RSA encryption.");


function get_random_saying() {
    $sayings = $GLOBALS['sayings'];
    $arr_length = count($sayings);
    $random = mt_rand(0, $arr_length-1);
    return $sayings[$random];
}

function output_flag() {
    $flag = 'The flag is :- pctf{4u1h3ntic4Ti0n.4nd~4u1horiz4ti0n_diff3r}';
    return $flag;
}

?>
