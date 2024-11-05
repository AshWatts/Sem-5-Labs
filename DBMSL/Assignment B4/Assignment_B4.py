from pymongo import MongoClient

def main():
    try:
        client = MongoClient("localhost", 27017)
        database = client["Institute"]
        collection = database["persons"]
        
        print("Success\n")

        while True:
            print("Menu Options:")
            print("1. Insert")
            print("2. Find")
            print("3. Update")
            print("4. Delete")
            print("5. Exit")
            choice = int(input("Enter your choice here: "))
            print()

            if choice == 1:
                name = input("Enter the name of the person: ")
                surname = input("Enter the surname of the person: ")
                id = int(input("Enter the id of the person: "))
                age = int(input("Enter the age of the person: "))
                
                doc = {"Name": name, "Surname": surname, "age": age, "id": id}
                collection.insert_one(doc)
                print("Document inserted successfully.\n")

            elif choice == 2:
                id = int(input("Enter the id of the person to find: "))
                person = collection.find_one({"id": id})
                if person:
                    print("Found:", person)
                else:
                    print("No person found with that id.")
                print()

            elif choice == 3:
                id = int(input("Enter the id of the person to update: "))
                new_age = int(input("Enter the new age: "))
                result = collection.update_one({"id": id}, {"$set": {"age": new_age}})
                if result.modified_count > 0:
                    print("Document updated successfully.")
                else:
                    print("No document found with that id.")
                print()

            elif choice == 4:
                id = int(input("Enter the id of the person to delete: "))
                result = collection.delete_one({"id": id})
                if result.deleted_count > 0:
                    print("Document deleted successfully.")
                else:
                    print("No document found with that id.")
                print()

            elif choice == 5:
                print("Exiting the program.\n")
                break

            else:
                print("Invalid choice. Please try again.\n")

    except Exception as e:
        print("Error:", e)

    finally:
        client.close()

if __name__ == "__main__":
    main()
