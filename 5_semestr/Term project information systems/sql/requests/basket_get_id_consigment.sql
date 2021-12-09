SELECT *
FROM consignmentnote
WHERE idConsignmentNote=LAST_INSERT_ID();