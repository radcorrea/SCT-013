PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;
CREATE TABLE sctLeitura (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, estado TEXT, data DATE, hora TIME);
INSERT INTO sctLeitura VALUES(1,'Desligado','2018-11-25','16:43:10');
INSERT INTO sctLeitura VALUES(2,'Desligado','2018-11-25','16:43:12');
INSERT INTO sctLeitura VALUES(3,'Desligado','2018-11-25','16:43:16');
INSERT INTO sctLeitura VALUES(4,'Ligado','2018-11-25','16:44:17');
INSERT INTO sctLeitura VALUES(5,'Desligado','2018-11-25','16:44:49');
INSERT INTO sctLeitura VALUES(6,'Desligado','2018-11-25','16:45:13');
INSERT INTO sctLeitura VALUES(7,'Desligado','2018-11-25','16:45:22');
INSERT INTO sctLeitura VALUES(8,'Desligado','2018-11-25','16:45:30');
INSERT INTO sctLeitura VALUES(9,'Ligado','2018-11-25','16:45:38');
INSERT INTO sctLeitura VALUES(10,'Ligado','2018-11-25','16:45:43');
INSERT INTO sctLeitura VALUES(11,'Ligado','2018-11-25','16:45:45');
INSERT INTO sctLeitura VALUES(12,'Ligado','2018-11-25','16:45:50');
INSERT INTO sctLeitura VALUES(13,'Ligado','2018-11-25','16:45:53');
INSERT INTO sctLeitura VALUES(14,'Desligado','2018-11-25','16:45:58');
INSERT INTO sctLeitura VALUES(15,'Desligado','2018-11-25','16:46:02');
INSERT INTO sctLeitura VALUES(16,'Desligado','2018-11-25','16:46:09');
INSERT INTO sctLeitura VALUES(17,'Desligado','2018-11-25','16:46:16');
INSERT INTO sctLeitura VALUES(18,'Desligado','2018-11-25','16:46:23');
INSERT INTO sctLeitura VALUES(19,'Desligado','2018-11-25','18:22:10');
INSERT INTO sctLeitura VALUES(20,'Desligado','2018-11-25','18:22:10');
INSERT INTO sctLeitura VALUES(21,'Ligado','2018-11-25','18:22:18');
INSERT INTO sctLeitura VALUES(22,'Ligado','2018-11-25','18:22:18');
INSERT INTO sctLeitura VALUES(23,'Desligado','2018-11-25','18:22:34');
INSERT INTO sctLeitura VALUES(24,'Desligado','2018-11-25','18:22:34');
DELETE FROM sqlite_sequence;
INSERT INTO sqlite_sequence VALUES('sctLeitura',24);
CREATE INDEX idx_sctLeitura ON sctLeitura(estado, data, hora);
COMMIT;
