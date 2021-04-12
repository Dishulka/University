SELECT idClient, Name, Adress, DateTotalWeight, MAX(TotalWeight)
FROM customer
WHERE month(DateTotalWeight) = 3 AND year(DateTotalWeight) = 2016 
GROUP BY idClient, Name, Adress, DateTotalWeight