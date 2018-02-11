<?php

function article_not_found($name) {
    echo "<br><center>";
    echo "File \"$name\" not found !!";
    echo "</center>";
    die();
}

function sanitize($filename) {
    $evil_chars = array("php:", "secret/flag_7258689d608c0e2e6a90c33c44409f9d.txt");
    foreach ($evil_chars as $value) {
        if( strpos($filename, $value) !== false) {
            echo "You naughty cheat !!<br>";
            die();
        }
    }

    $bad_chars = array("./", "../");
    foreach ($bad_chars as $value) {
        $filename = str_replace($value, "", $filename);
    }

    $temp = new SplFileInfo($filename);
    $ext = $temp->getExtension();

    if( $ext !== "txt") {
        $filename = $filename.".txt";
    }

    return $filename;

}

?>
