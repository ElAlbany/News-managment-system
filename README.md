# News-managment-system

our system will be divided into 2 classes : 
 --------------------------------------------------

 1- UserRepository : 
 
            This will hold all admin and user functionalities
    
     General functions :
        
             1- log in : you will take username and password as arugments to check weather the account is user or admin
                         , then return his index to main to use it in other functions to get work easier for others
        
             2- register : when you take username it should be unique for both admin and user , no 2 account  have the same username 
                           so maybe you need to create additional 2 functions to check username in admin list and user list 
    
       ----------------------------------------------------------------------------------------------------
    
       Admin functions :
    
               1- add new category : you need to create new category and push it to vector that holds all categories.
            
               2- post news : you will ask the admin to enter news details except the rate
                               will be  done automatically when new user add rate .
                               for category admin must select one of the existing categories and this can be done 
                               in update and not neccessery in this stage.
            
               3- display all news : display all existing news in numeric order ([1] article1 , [2]article2 .....etc)  and if there isnt , so display message (there isnt news right now)
                                     if admins pressed on one of them then show its details. (number is also index  this will let work be easier)
            
               4- remove news : display all news then remove one of selecting news and add button back .
            
               5- update news : admin can edit in any information of the news exept the rate, 
                                in this stage you can add category for the news if it wasnt chosen yet.
            
               6- displayAvgRate : display all news  so admin can select one to see its rate .
            
               7- add new admin : (very clear)
            
               8- remove admin : display all admins username like ([1]admin1 [2] admin2 ... etc) 
                                 this numeric order is also can be used for index (except himself)
    
       ----------------------------------------------------------------------------------------------------------------------------

   2- News : 

       User functions :

               1- search : display whatever matches which user types .

               2- display latest news : you can display last  5 news has beed added  , or all news but in descending order
                                        (from last index to first index)

               3- search by category : (very clear)

               4- rate news : display all news for user in their numeric order ( [1]  first, [2] second  , etc...) 
                              and ask him to enter a number and this is also its index or index -1 ,whatever ,
                              and add this rate with his username to the map and ((( build function ))) that sum all rates and 
                              divide on their size ,and reassign it in the news rate

                              ((note : force him to enter rate between 1 and 5 inclusive))

               5- bookmarking : let user select article to add it to his favourite articles (vector hold article title as a reference)
                              user has 3 options [1] add [2] remove [3] back ( to back to main menu,whatever) .

               6- trending news  : display all news in descending order based on thier rates to show the highest rates first 
                                    you can create  
       

   
