# News-managment-system

out system will be divided into 2 classes : 
 --------------------------------------------------

 1- UserRepository : 
 
            This will hold all admin and user functionalities
    
     General functions :
        
             1- log in : you will take username and password as arugments to check weather the account is user or admin
                         if it was user , then return his index to main to use it in other functions to get work easier for others
        
             2- register : when you take username it should be unique for both admin and user , no 2 account  have the same username 
                           so maybe you need to create additional 2 functions to check username in admin list and user list 
    
       ----------------------------------------------------------------------------------------------------------------------
    
       Admin functions :
    
               1- add new category : you need to create new category and push it to vector that holds all categories.
            
               2- post news : you will ask the admin to enter news details except the rate will be  done automatically when new user add rate .
                               for category admin must select one of the existing categories and this can be done in update and not neccessery in this stage.
            
               3- display all news : display all existing news and if there isnt , so display message (there isnt news right now)
                                     if admins pressed on one of them then show its details.
            
               4- remove news : display all news then remove one of selecting news and add button back .
            
               5- update news : admin can edit in any information of the news exept the rate, in this stage you can add category for the news if it wasnt chosen yet.
            
               6- displayAvgRate : display all news  so admin can select one to see its rate .
            
               7- add new admin : (very clear)
            
               8- remove admin : display all admins username like ([1]admin1 [2] admin2 ... etc) this numeric order is also can be used for index
    
       ---------------------------------------------------------------------------------------------------------------------------------------------------\
    
       

   
