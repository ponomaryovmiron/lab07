from flask import Flask
import pymysql
import os
import time

app = Flask(__name__)

def get_connection():
    for _ in range(30):
        try:
            return pymysql.connect(
                host=os.getenv("DB_HOST", "db"),
                user=os.getenv("DB_USER", "labuser"),
                password=os.getenv("DB_PASSWORD", "labpass"),
                database=os.getenv("DB_NAME", "labdb"),
                charset="utf8mb4"
            )
        except pymysql.err.OperationalError:
            time.sleep(2)

    raise RuntimeError("Cannot connect to database")

@app.route("/")
def index():
    conn = get_connection()
    cur = conn.cursor()

    cur.execute("SELECT name FROM tasks ORDER BY id")
    tasks = cur.fetchall()

    cur.close()
    conn.close()

    html = """
    <!DOCTYPE html>
    <html>
    <head>
        <meta charset="UTF-8">
        <title>Lab07 Docker</title>
    </head>
    <body>
        <h1>Список задач</h1>
        <ul>
    """

    for task in tasks:
        html += f"<li>{task[0]}</li>"

    html += """
        </ul>
    </body>
    </html>
    """

    return html

if __name__ == "__main__":
    print("Hello, Docker!")
    app.run(host="0.0.0.0", port=5000)
