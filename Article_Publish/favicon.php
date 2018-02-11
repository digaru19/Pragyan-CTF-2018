<?php

$fav_id = !empty($_GET['id']) ? $_GET['id'] : '1';
$favicon = $fav_id;
$id = (int)$fav_id;

if($id >= 1 and $id <= 6) {
    $favicon= "fav".$id.".png"; 
}

header("Content-Type: image/x-icon"); 
header("Pragma-directive: no-cache");
header("Cache-directive: no-cache");
header("Cache-control: no-cache");
header("Pragma: no-cache");
header("Expires: 0");

$filepath = "./favicons/".$favicon;
$temp = new SplFileInfo($filepath);
$ext = $temp->getExtension();

if($ext !== "" and $ext !== "png" and $ext !== "php" ) {
    echo "Invalid extension '$ext' specified";
    die();
}

if(!file_exists($filepath)) {
    echo "File '$filepath' does not exist";
    die();
}

readfile($filepath); 

?>
