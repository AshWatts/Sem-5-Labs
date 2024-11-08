import mysql.connector
from mysql.connector import Error

def connect_to_mysql():
    """Establish a connection to the MySQL database."""
    try:
        connection = mysql.connector.connect(
        host='10.10.13.97',     
        database='te31283_db',  
        user='te31283',          
        password='te31283'      
        )
        if connection.is_connected():
            print("Connected to MySQL database!")
            return connection
    except Error as e:
        print("Error while connecting to MySQL:", e)
        return None

def add_circle_area(connection, radius, area):
    """Add a new record to the Circle_Area table and print the added record."""
    try:
        cursor = connection.cursor()
        query = "INSERT INTO Circle_Area (radius, area) VALUES (%s, %s)"
        values = (radius, area)
        cursor.execute(query, values)
        connection.commit()
        print("Record added successfully!")
        print("Added Record:")
        print_circle_area_record(connection, radius)
    except Error as e:
        print("Error while adding record:", e)
    finally:
        cursor.close()

def edit_circle_area(connection, radius, new_area):
    """Edit an existing record's area based on radius and print the updated record."""
    try:
        cursor = connection.cursor()
        query = "UPDATE Circle_Area SET area = %s WHERE radius = %s"
        values = (new_area, radius)
        cursor.execute(query, values)
        connection.commit()
        if cursor.rowcount > 0:
            print("Record updated successfully!")
            # Fetch and print the updated record
            print("Updated Record:")
            print_circle_area_record(connection, radius)
        else:
            print("No record found with the given radius.")
    except Error as e:
        print("Error while updating record:", e)
    finally:
        cursor.close()

def delete_circle_area(connection, radius):
    """Delete a record from the Circle_Area table based on radius and print the deleted record."""
    try:
        cursor = connection.cursor()
        # Fetch the record before deleting
        print("Record to be deleted:")
        print_circle_area_record(connection, radius)
        
        query = "DELETE FROM Circle_Area WHERE radius = %s"
        values = (radius,)
        cursor.execute(query, values)
        connection.commit()
        if cursor.rowcount > 0:
            print("Record deleted successfully!")
        else:
            print("No record found with the given radius.")
    except Error as e:
        print("Error while deleting record:", e)
    finally:
        cursor.close()

def print_circle_area_record(connection, radius):
    """Print the details of a record from the Circle_Area table based on radius."""
    try:
        cursor = connection.cursor()
        query = "SELECT * FROM Circle_Area WHERE radius = %s"
        cursor.execute(query, (radius,))
        record = cursor.fetchone()
        if record:
            print(f"Radius: {record[0]}, Area: {record[1]}")
        else:
            print("No record found with the given radius.")
    except Error as e:
        print("Error while fetching record:", e)
    finally:
        cursor.close()

def main():
    connection = connect_to_mysql()
    if connection:
        radius_to_add = 5
        area_to_add = 78.54  
        add_circle_area(connection, radius_to_add, area_to_add)
        
        radius_to_edit = 5
        new_area = 80.0  
        edit_circle_area(connection, radius_to_edit, new_area)
        
        radius_to_delete = 5
        delete_circle_area(connection, radius_to_delete)
        
        connection.close()

if __name__ == "__main__":
    main()