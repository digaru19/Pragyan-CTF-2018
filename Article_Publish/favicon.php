<?php

error_reporting(0);

$fav_id = !empty($_GET['id']) ? $_GET['id'] : '1';

header("Content-Type: image/x-icon"); 
header("Pragma-directive: no-cache");
header("Cache-directive: no-cache");
header("Cache-control: no-cache");
header("Cache-Control: no-store");
header("Pragma: no-cache");
header("Expires: 0");


$favicon = $fav_id;
$filepath = "./favicons/".$favicon;


if(file_exists($filepath . ".png")) {
    $favicon = $filepath . ".png";
}
else if (file_exists($filepath . ".php")) {
    $favicon = $filepath . ".php";
}
else if (file_exists($filepath . ".ico")) {
    $favicon = $filepath . ".ico";
}
else {
    $err_msg = "No files named '$filepath.png', '$filepath.ico'  or '$filepath.php' found ";
    echo $err_msg;
    die();
}


if(!file_exists($favicon)) {
    echo "File '$filepath' does not exist";
    die();
}

readfile($favicon); 

?>
