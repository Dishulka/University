SELECT e.Surname
FROM employee e
LEFT JOIN consignmentnote cn ON (e.idEmployee = cn.idEmployee)
WHERE idConsignmentNote IS NULL