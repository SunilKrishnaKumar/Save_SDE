use save_db;
SELECT *
FROM Transactions
INNER JOIN Acc_info 
ON Transactions.acc_number = Acc_info.acc_number
WHERE Transactions.merchant_state != Acc_info.state