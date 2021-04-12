CREATE VIEW sectionCount (Section, Position, quantity)
AS (
SELECT Section, Position, COUNT(*)
FROM employee
GROUP BY Section, Position
);

SELECT DISTINCT Section
FROM sectionCount
WHERE quantity = (SELECT MAX(quantity) FROM sectionCount WHERE Position = "Manager")



