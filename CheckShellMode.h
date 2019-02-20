int checkmode(int argc)
{
  if(argc >1)  //user entered commands 
  {
    return(true);
  }
  else if(argc == 1)  //user did not enter any commands 
  {
    return(false);
  }
  else  //error check
  {
    return(false);
  }
}