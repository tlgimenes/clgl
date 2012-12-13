//--------------------------------//
//                                //
//  Author: Tiago Lobato Gimenes  //
//  email: tlgimenes@gmail.com    //
//                                //
//--------------------------------//

__kernel void hello(__global char* string)
{
  size_t cur = get_global_id(0);
  
  string[cur] += 1;

  return;
}
