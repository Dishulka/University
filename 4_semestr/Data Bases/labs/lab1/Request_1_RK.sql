SELECT cn.idConsignmentNote, cn.NoteDate, e.Surname, c.TotalWeight
FROM consignmentnote cn
JOIN employee e ON cn.idEmployee = e.idEmployee
JOIN customer c ON cn.idClient = c.idClient
