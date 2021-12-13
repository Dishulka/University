SELECT Name, SUM(Weight)

FROM consignmentnote
         JOIN customer
              ON customer.idClient = consignmentnote.idClient
WHERE YEAR(consignmentnote.NoteDate) = $year
GROUP BY consignmentnote.idClient