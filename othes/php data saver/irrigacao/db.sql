DROP DATABASE IF EXISTS irrigacao;
CREATE DATABASE irrigacao;

USE irrigacao;

CREATE TABLE measures (
    measures_id INT AUTO_INCREMENT PRIMARY KEY,
    time DATETIME,
    value INT,
    insertTime DATETIME
);

-- INSERT INTO measures (TIME, VALUE, insertTime) VALUES ("2022-10-13", 10, NOW()),("2022-10-14", 11, NOW());