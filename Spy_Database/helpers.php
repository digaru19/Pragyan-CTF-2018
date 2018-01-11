<?php

function redirect($url) {
    ob_start();
    header('Location: '.$url);
    ob_end_flush();
    die();
}

function sanitize($str) {
    $str = strtolower($str);
    if( strpos($str, 'union') !== false ) {
        redirect("/ss/B/hacker.html");
        die();
    }
    return $str;
}

?>