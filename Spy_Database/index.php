<!DOCTYPE html>
<html>

<head>
    <title>Secret Service</title>

<style type="text/css">
 #search {
    margin-top: 60px;
    font-size: 10px;
    margin-bottom: 20px;
 }

#agent {
    width: 60%;
    border: 2px solid black;
    border-radius: 15px;
    display: flex;
    margin-left: auto;
    margin-right: auto;
    margin-top: 10px;
    padding: 10px;
}

.ag_img {
    margin: 5px;
    margin-left: 10px;
    margin-right: 10px;
    height: 135px;
    border: 2px solid grey;
    float: left;
}

.ag_info {
    margin-left: 10px;
    line-height: 20px;
}

</style>
</head>

<body bgcolor='#e8f8f5'>

<center>
<h2> Animal Spy Database </h2>

<div id='search'>
<form id='search_form' method="POST" action='#' >
    <input id='spy_name' autocomplete="off" value='' type="text" name="spy_name">
    <input type="submit" value='Search'>
</form>
</div>
</center>

<?php

require "helpers.php";

$conn = mysqli_connect('localhost', 'root', 'password', 'blind');
if (! $conn) {
    die("DB Connection failed !!");
}

$search = '%';

if( !empty($_POST['spy_name'])) {
    $search = base64_decode($_POST['spy_name']);
    $search = sanitize($search);
    echo "<br> <center> You queried for : <i>$search</i> </center> <br>";
}

$query = "SELECT * from animals where name LIKE '%$search%'";
$result = mysqli_query($conn, $query);

$agent_div = "
<div id='agent'>
    <img class='ag_img' src='images/%d.jpg' alt='Spy Image'/>
    <div class='ag_info'>
        <b> Name : </b> %s <br>
        <b> Age : </b> %d <br>
        <b> Experience : </b> %d <br>
        <b> Description : </b> %s <br>
    </div>
</div>
";

if($result) {
    while ($row = mysqli_fetch_assoc($result)) {
        printf($agent_div, $row["id"], $row["name"], $row["age"], $row["experience"], $row["description"]);
    }
}
else {
    echo "<br> <center> Sorry, we couldn't find any agent with the given name! </center> <br>";
}

?>

<script src='encode.js' type="text/javascript" ></script>
</body>
</html>
