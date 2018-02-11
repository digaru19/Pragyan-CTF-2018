

<!DOCTYPE html>
<html>
  <head>

  <?php
    $favicon_id = mt_rand(1,6);
    echo "<link rel='shortcut icon' href='favicon.php?id=$favicon_id' type='image/x-icon'>";
  ?>

    <meta charset="UTF-8">
    <title>Read Articles</title>

  <link rel="stylesheet" href="css/bootstrap.min.css">

  </head>

  <body>
    
    <center>
    <?php
        error_reporting(0);

        require "fetch.php";
        require "helpers.php";

        $filename = !empty($_GET['file']) ? $_GET['file'] : "";

        if($filename === "") {
            $files = scandir('./articles');
            foreach($files as $i) {
                $t = explode(".txt", $i)[0];
                echo "<h4><a href='?file=$t'> $t </a> </h4><br>";
            }
        }
        else {
            $filename = sanitize($filename);
            $file_contents = read_article($filename);

            echo $file_contents;
        }


    ?>
    </center>


    
  </body>

</html>
