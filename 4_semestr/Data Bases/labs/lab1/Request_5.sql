SELECT idClient, Sum(Weight)
FROM consignmentnote
WHERE YEAR(NoteDate)=2013
group by idClient