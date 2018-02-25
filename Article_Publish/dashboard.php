

<!DOCTYPE html>
<html>
  <head>

  <?php
    $favicon_id = mt_rand(1,7);
    echo "<link rel='shortcut icon' href='favicon.php?id=$favicon_id' type='image/x-icon'>";
  ?>

    <meta charset="UTF-8">
    <title>El33t Articles Hub</title>

  <link rel="stylesheet" href="css/bootstrap.min.css">
  <style type="text/css">
      #container {
        background-color: #fcf3cf   ;
        width: 60%;
        border: 1px solid grey;
        padding: 10px;
        margin: auto;
        margin-top: 10px;
        margin-bottom: 30px;
      }

      #container p {
        padding: 10px;
        font-size: 16px;
      }

      #header {
        height: 100px;
        margin: 20px;
        text-align: center;
        font-size: 24px;
      }

      body {
        background-color:  #f9e79f  ;
      }

  </style>

  </head>

  <body>

  <div id='header'>
        <b><u> El33t Articles Hub </u> </b>
  </div>

    <div id='container'>
    <?php
        error_reporting(0);
        require "fetch.php";
        require "helpers.php";

        $filename = !empty($_GET['file']) ? $_GET['file'] : "";

        if($filename !== "") {

            $filename = sanitize($filename);
            $file_contents = read_article($filename);
            echo "<p>";
            echo $file_contents;
            echo "</p>";
        }
        else {
            $files = scandir('./articles');
            echo "<ul>";
            foreach($files as $i) {
                $temp = new SplFileInfo($i);
                $ext = $temp->getExtension();
                if($ext !== "txt")
                    continue;
                $t = explode(".txt", $i)[0];
                echo "<li><h4><a href='?file=$t'> $t </a> </h4></li>";
            }
            echo "</ul>";
        }

    ?>

    </div>
    <center>
        <p> Copywrite &copy; El33t Articles Hub </p>
    </center>
  </body>

</html>
