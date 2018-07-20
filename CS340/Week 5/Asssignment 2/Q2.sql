INSERT INTO client (first_name, last_name, dob)
VALUES
('Sara', 'Smith', '1970-01-02'),
('Miguel', 'Cabrera', '1988-02-02'),
('Bo', 'Chang', '1985-03-02');

INSERT INTO employee (first_name, last_name, dob, date_joined)
VALUES
('Ananya', 'Jaiswal', '1975-01-02', '2009-01-01'),
('Michael', 'Fern', '1980-10-18', '2013-06-05'),
('Abdul', 'Rehman', '1984-03-21', '2013-11-10');

INSERT INTO project (cid, name, notes)
VALUES
((SELECT id FROM client WHERE first_name LIKE 'Sara' and last_name LIKE 'Smith' LIMIT 1),
'Diamond', 'Should be done by Jan 2019'),
((SELECT id FROM client WHERE first_name LIKE 'Bo' AND last_name LIKE 'Chang' LIMIT 1),
'Chan\'g', 'Ongoing maintenance'),
((SELECT id FROM client WHERE first_name LIKE 'Miguel' AND last_name LIKE 'Cabrera' LIMIT 1),
'The Robinson Project', NULL);

INSERT INTO works_on (eid, pid, start_date)
VALUES
((SELECT id FROM employee WHERE first_name LIKE 'Ananya' AND last_name LIKE 'Jaiswal' LIMIT 1),
(SELECT id FROM project WHERE name LIKE 'Chan\'g'), '2012-01-01'),
((SELECT id FROM employee WHERE first_name LIKE 'Michael' AND last_name LIKE 'Fern' LIMIT 1),
(SELECT id FROM project WHERE name LIKE 'The Robinson Project'), '2013-08-08'),
((SELECT id FROM employee WHERE first_name LIKE 'Abdul' AND last_name LIKE 'Rehman' LIMIT 1),
(SELECT id FROM project WHERE name LIKE 'Diamond'), '2014-09-11');