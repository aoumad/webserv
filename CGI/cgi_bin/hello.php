<?PHP
echo "<HTML>";
echo "<HEAD>";
echo "<TITLE>Test</TITLE>";
echo "</HEAD>";
echo "<BODY>";
if ($_SERVER['REQUEST_METHOD'] == 'GET')
    echo "<H1>hello ". $_GET["name"] . " " . $_GET["last_name"] . "</H1>";
else
    echo "<H1>hello ". $_POST["name"] . " " . $_POST["last_name"] . "</H1>";
echo "</BODY>";
echo "</HTML>";
?>