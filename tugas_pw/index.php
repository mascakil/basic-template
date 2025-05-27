<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <title>Kalkulator FPB</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background: #f0f0f0;
            display: flex;
            height: 100vh;
            justify-content: center;
            align-items: center;
        }
        .container {
            background: #fff;
            padding: 20px 30px;
            border-radius: 10px;
            box-shadow: 0 4px 10px rgba(0,0,0,0.1);
            width: 300px;
            text-align: center;
        }
        input[type="number"] {
            width: 100%;
            padding: 8px;
            margin: 10px 0;
            border-radius: 5px;
            border: 1px solid #ccc;
        }
        input[type="submit"] {
            background: #007BFF;
            color: white;
            border: none;
            padding: 10px;
            width: 100%;
            border-radius: 5px;
            cursor: pointer;
        }
        .result {
            margin-top: 20px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>Hitung FPB</h2>
        <form method="POST">
            <input type="number" name="angka1" placeholder="Masukkan angka pertama" required>
            <input type="number" name="angka2" placeholder="Masukkan angka kedua" required>
            <input type="submit" value="Hitung FPB">
        </form>

        <?php
        function hitungFPB($a, $b) {
            while ($b != 0) {
                $temp = $b;
                $b = $a % $b;
                $a = $temp;
            }
            return $a;
        }

        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $angka1 = (int)$_POST["angka1"];
            $angka2 = (int)$_POST["angka2"];
            $fpb = hitungFPB($angka1, $angka2);
            echo "<div class='result'>FPB dari $angka1 dan $angka2 adalah <strong>$fpb</strong></div>";
        }
        ?>
    </div>
</body>
</html>
