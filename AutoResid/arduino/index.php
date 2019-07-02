<?php
    $dados = array();
    if(!empty($_POST['state'])){
        if(!empty($_POST['r1'])){
            $dados["r1"] = 1;
        } else{
            $dados["r1"] = 0;
        }

        if(!empty($_POST['r2'])){
            $dados["r2"] = 1;
        } else{
            $dados["r2"] = 0;
        }

        if(!empty($_POST['r3'])){
            $dados["r3"] = 1;
        } else{
            $dados["r3"] = 0;
        }

        if(!empty($_POST['r4'])){
            $dados["r4"] = 1;
        } else{
            $dados["r4"] = 0;
        }

        if(!empty($_POST['btn'])){
            $dados["btn"] = 1;
        } else{
            $dados["btn"] = 0;
        }

        if(!empty($_GET['btn'])){
            $dados["btn"] = 1;
        } else{
            $dados["btn"] = 0;
        }

        if(!empty($_POST['r1n'])){
            $dados["r1"] = $_POST['r1n'];
        }

        if(!empty($_POST['r2n'])){
            $dados["r2"] = $_POST['r2n'];
        }

        if(!empty($_POST['r3n'])){
            $dados["r3"] = $_POST['r3n'];
        }

        if(!empty($_POST['r4n'])){
            $dados["r4"] = $_POST['r4n'];
        }
        //abrindo o arquivo para a escrita

        $fp = fopen('example.json', 'w');

        //escrevendo os dados no arquivo

         fwrite($fp, json_encode($dados));

        //fechando o arquivo
         fclose($fp);
    }

         // Atribui o conteúdo do arquivo para variável $arquivo
        $arquivo = file_get_contents('example.json');
        
        // Decodifica o formato JSON e retorna um Objeto
        $json = json_decode($arquivo);
        
        



?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Document</title>
    <style>
        .bola1{
            border-radius: 300px;
            height: 40px;
            width: 40px;
            background: #096921;
        }
        .bola2{
            border-radius: 300px;
            height: 40px;
            width: 40px;
            background: #096921;
        }
        .bola3{
            border-radius: 300px;
            height: 40px;
            width: 40px;
            background: #096921;
        }
        .bola4{
            border-radius: 300px;
            height: 40px;
            width: 40px;
            background: #096921;
        }
        button{
            
            border-radius: 5px;
            border-color: #55FA99;
            background: #10AADD;
            color: #FFFFFF;
            height: 150px;
            width: 304px;
            font-size: 30px;
        }
        input{
            text-align: center;
            height: 50px;
            width: 50px;
            border-radius: 400px;
        }
        .p1{
            background: #daf0de
        
        }
        .p2{
            background: #daf0de

        }
        .p3{
            background: #daf0de

        }
        .p4{
            background: #daf0de

        }
        footer{
            border-radius: 5px;
            weight: 300px;
            font-size: 30px;
            padding-top: 30px;
            padding-left: 10px;
            padding-right: 10px;
            color: red;
            background: black;
        }
        span{
            color: white;
            background: black;
        }
    </style>
    <?php
        if($json->r1 == 0){
            echo " <style>.p1{ background: #f0dada; } .bola1{ background: #FF3200; }</style> ";
            
        }
        if($json->r2 == 0){
            echo " <style>.p2{ background: #f0dada; } .bola2{ background: #FF3200; }</style> ";
        }
        if($json->r3 == 0){
            echo " <style>.p3{ background: #f0dada; } .bola3{ background: #FF3200; }</style> ";
        }
        if($json->r4 == 0){
            echo " <style>.p4{ background: #f0dada; } .bola4{ background: #FF3200; }</style> ";
        }
        ?>
</head>
<body>

    <form action="<?php echo $_SERVER['PHP_SELF'];?>" method="post">
    
    <table class="table table-hover">
        <thead>
            <tr>
                <th>R1 <p class="p1"><canvas class="bola1" ></canvas></p></th>
            
                <th>R2 <p class="p2"><canvas class="bola2" ></canvas></p></th>
            
                <th>R3 <p class="p3"><canvas class="bola3" ></canvas></p></th>
           
                <th>R4 <p class="p4"><canvas class="bola4" ></canvas></p></th>
                
            </tr>
        </thead>
        <tbody>
            <tr>     
                <td>
                    <label class="btn btn-primary">
                    
                        <input type="checkbox" name="r1" id="r1" />
                        <input type="number" name="r1n" id="input" />
                    </label>
                </td>
                <td>
                    <label class="btn btn-primary">
                        <input type="checkbox" name="r2" id="r2" />
                        <input type="number" name="r2n" id="input" />
                    </label>
                </td>
                <td>
                    <label class="btn btn-primary">
                        <input type="checkbox" name="r3" id="r3" />
                        <input type="number" name="r3n" id="input" />
                    </label>
                </td>
                <td>
                    <label class="btn btn-primary">
                        <input type="checkbox" name="r4" id="r4" >
                        <input type="number" name="r4n" id="input" />
                    </label>
                </td>
            </tr>
        </tbody>
    </table> 
    <input type="hidden" name="state" value = 1 />
    <button type="submit">Enviar</button>
    </form>
    <footer><span>TESTE</span> ARDUINO <br> <span>TESTE</span> ETHERNET</footer>
    <?php
    echo "<script>";
        if($json->r1 == 1){
            echo "document.getElementById('r1').setAttribute('checked', '');";
            
        }
        if($json->r2 == 1){
            echo "document.getElementById('r2').setAttribute('checked', '');";
        }
        if($json->r3 == 1){
            echo "document.getElementById('r3').setAttribute('checked', '');";
        }
        if($json->r4 == 1){
            echo "document.getElementById('r4').setAttribute('checked', '');";
        }
        echo "</script>";
        ?>
</body>
</html>