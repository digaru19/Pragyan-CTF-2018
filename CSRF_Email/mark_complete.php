<?

$secret = $_COOKIE['_secret_key'];
$session_id = $_COOKIE['_saved_sess_id'];

if(empty($secret)) {
    die("This action is available only for admins.");
}

if( !empty($session_id))
    session_id($session_id);

session_start();

require "helpers.php";
require "secret.php";

if( ! isset($_SESSION['email']))

$sess_email = $_SESSION['email'];
$sess_team_id = $_SESSION['team_id'];
$team_id = $_GET['team_id'];
$challenge_id = $_GET['chal_id'];

$timestamp = getdate();

if( ($sess_team_id !== $team_id) || ($org_chal_id !== $challenge_id) )
    die("This action is available only for admins.");

if($org_secret !== $secret) {
    die("This action is available only for admins.");
}

mark_chal_complete($sess_team_id, $sess_email);


?>
