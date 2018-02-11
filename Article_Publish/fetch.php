<?php


function read_article($filename) {
    $file_content = file_get_contents("./articles/".$filename);

    if($file_content === false)
        article_not_found($filename);
    else
        return $file_content;

}

?>
