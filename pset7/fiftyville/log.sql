-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get crime scene report info for date & street of crime
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Info Gained: took place @ 10:15am  & mentions the courthouse @ the courthouse interview condusted with 3 witnesses present @ the time

-- check interviews for who gave interview on July 28th:
SELECT name, transcript FROM interviews
WHERE month = 7 AND day = 28;

-- info gained:
-- Ruth said: Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame. 
-- Eugene said: I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I 
-- was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond said: As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard
-- the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other 
-- end of the phone to purchase the flight ticket.

-- Check courthouse security logs to see who left the courthouse at 10:15 - 10:26 (within 10 minuts of crime) on july 28
SELECT activity, id, hour, minute, license_plate FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26 AND activity = "exit";
 
-- Get people names from license plate #'s
SELECT name FROM people
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= "15" AND minute < "25" AND activity = "exit");

-- SUSPECTS returned : Patrick Amber Elizabeth Roger Danielle Russell Evelyn Ernest

-- check who was @ ATM on FIFER street withdrawing $
SELECT account_number FROM atm_transactions
WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw";

-- cross with bank_accounts to get names
SELECT name FROM people
WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions
WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND transaction_type = "withdraw"));

-- SUSPECTS remaining: Elizabeth Danielle Russell Ernest

-- check for earliest flight out of fiftyville July 29 then accomplice purchased tickets
SELECT id FROM airports
WHERE city = "Fiftyville";

SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1;

SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

SELECT name FROM people
WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1));


-- SUSPECTS FOUND: Danielle Ernest

-- SEE who made al ess than 1 minute phone call on day of crime
SELECT caller, duration FROM phone_calls
WHERE month = 7 AND day = 28 AND duration < 60;

SELECT name FROM people
WHERE phone_number in (SELECT caller FROM phone_calls
WHERE month = 7 AND day = 28 AND duration < 60);

SUSPECT FOUND: Ernest

-- Find destination: 
SELECT full_name, city FROM airports
WHERE id = (SELECT destination_airport_id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = "Fiftyville") AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);


-- find what time Ernest left courthouse
SELECT receiver FROM phone_calls;

SELECT phone_number FROM people
WHERE name = "Ernest";

SELECT receiver FROM phone_calls
WHERE caller = (SELECT phone_number FROM people
WHERE name = "Ernest") AND month = 7 AND day = 28;

SELECT name FROM people
WHERE phone_number = (SELECT receiver FROM phone_calls
WHERE caller = (SELECT phone_number FROM people
WHERE name = "Ernest") AND month = 7 AND day = 28);