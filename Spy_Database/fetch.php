<?php

$conn = mysqli_connect('localhost', 'root', 'password', 'blind');
if (! $conn) {
    die("DB Connection failed !!");
}

$t = base64_decode($_GET['id']);
#$t = ($_GET['id']);

echo "<br>****  $t  ****<br>";

$query = "SELECT * from images where name LIKE '$t'";
$result = mysqli_query($conn, $query);

if($result) {
    
    while ($row = mysqli_fetch_assoc($result)) {
        printf("<br> Image Name :- %s <br> Rating :- %s <br>", $row["name"], $row["rating"]);
    }

    echo "<br><br> FINISH";
}
else {
    echo "Sorry, we couldn't find any goat with the given name !";
}

?>
