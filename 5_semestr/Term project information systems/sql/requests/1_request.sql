SELECT Surname, Position
FROM employee
WHERE MONTH(HiredDate) = $month AND YEAR(HiredDate) = $year