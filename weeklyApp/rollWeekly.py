import random
import datetime
import pytz
from mysql.connector import connect, Error
import requests

# access credentials not checked in for security
MySQLUser = "xxx"
MySQLPassword = "xxx"
MySQLDatabase = "xxx"
WebHookURL = "xxx"

def getYearAndWeek():
    PacificTime = pytz.timezone('America/Los_Angeles')
    now = datetime.datetime.now(PacificTime)
    year, isoWeek, weekDay = now.isocalendar()
    return (year, isoWeek)

def randomSeed():
    random.seed()
    return random.randint(1, 4294967295)

def getSeedUrl(seed):
    return "https://randoblazer.com?race=1&seed=" + str(seed)

def dbWriteSeed(year, week, seed):
    # Use UTC time for the database entry
    creationTime = datetime.datetime.utcnow().isoformat(sep=' ')
    sql = f"""
    INSERT INTO `weekly_seeds` (`id`, `creation_date`, `year`, `week`, `seed`)
    VALUES (NULL, '{creationTime}', '{year}', '{week}', '{seed}');
    """
    # For testing
    #print(sql)
    #return

    try:
        with connect(
            host="localhost",
            user=MySQLUser,
            password=MySQLPassword,
            database=MySQLDatabase,
        ) as connection:
            with connection.cursor() as cursor:
                cursor.execute(sql)
                connection.commit()
                print("Wrote seed to database")

    except Error as e:
        print("mySQL error:", e)

def webHookAnnounce(year, week, seed):
    message = f"""\
It's that time again! Here is the weekly seed for {year} week {week}:
{getSeedUrl(seed)}
"""
    # For testing
    #print(message)
    #return

    req = requests.post(WebHookURL, json={'content': message})
    print("Webhook post status:", req.status_code)

def generateWeeklySeed():
    year, week = getYearAndWeek()
    seed = randomSeed()

    dbWriteSeed(year, week, seed)
    webHookAnnounce(year, week, seed)


if __name__ == "__main__":
    generateWeeklySeed()
