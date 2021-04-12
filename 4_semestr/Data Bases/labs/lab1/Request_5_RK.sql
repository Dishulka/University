SELECT e.Surname
FROM employee e
LEFT JOIN (SELECT idConsignmentNote, idEmployee
FROM consignmentnote
WHERE month(NoteDate) = 3 AND year(NoteDate) = 2013) as temp
ON (e.idEmployee = temp.idEmployee)
WHERE temp.idConsignmentNote IS NULL