<?php

include_once("conecction.php");


$url = "http://$espIp/cli/mostrarEApagarLeiturasDeSolo";


$qtdMax = 100;


$strquery = "INSERT INTO measures (TIME, value, insertTime) VALUES";
$flag_isthefisrt = true;
$theraAreMoreToRead = false;
$count = 0;
$nOfRequests = 0;
$qtdPerRequest;

do
{
    $nOfRequests++;
    $data = file_get_contents($url);
    // $data = file_get_contents("http://127.0.0.1/irrigacao/ex.txt");
    echo "data:\"$data\"\n";
    $data = str_replace("\r\n", "\n", $data);
    $lines = explode("\n", $data);
    foreach($lines as $iOfLine => $line)
    {
        if($line != "")
        {
            if($iOfLine == 0)
            {
                sscanf($line,"Medidas (%d/%d):",$qtdRead,$qtdTotal);
                echo "qtd: $qtdRead\ntotal: $qtdTotal\n\n";
                if($qtdRead != $qtdTotal)
                {
                    $theraAreMoreToRead = true;
                    // echo "tem mais\n";
                } 
            } 
            else if(stripos($line, ">") != -1)
            {
                $count++;
                $line = explode(">", $line);

                $error = false;

                if(strlen($line[0]) == 0 || strlen($line[1]) == 0) $error = true;

                try {
                    $line[0] = gmdate("Y-m-d H:i:s", intval($line[0]));
                    $line[1] = intval($line[1]);
                }
                catch (Exception $e) {
                    echo 'erro convertendo data e valor da leitura: ',  $e->getMessage(), "\n";
                    $error = true;
                    echo "erro";
                }

                if($error) $count--; 
                else 
                {
                    if($flag_isthefisrt) $flag_isthefisrt = false;
                    else $strquery .= ",";

                    $strquery .= " (\"$line[0]\",$line[1],NOW())";
                }
            }
        }
    }

    if($nOfRequests == 1) $qtdPerRequest = $count;
}
while($theraAreMoreToRead && ($count+$qtdPerRequest) <= $qtdMax);

echo "query: \"$strquery\"\n\n";
if($count != 0) $con->query($strquery);
  
$con->close();

?>