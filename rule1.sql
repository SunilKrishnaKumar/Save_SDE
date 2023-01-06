use save_db;
SELECT t.* FROM Transactions t  
JOIN (SELECT DISTINCT merchant_cat_code FROM  Transactions) m
ON t.merchant_cat_code = m.merchant_cat_code
where t.transaction_amount > (10)*(SELECT avg(transaction_amount) FROM Transactions where merchant_cat_code = t.merchant_cat_code) 