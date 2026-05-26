 __attribute__((section(".ipe_entry"))) uint16_t simple_branch_internal(uint16_t entry)
{
  int result = 0;
  if (entry == private_key)
  {
    result += 5;
  }
  else
  {
     asm __volatile__("nop\n\tnop");
  }
  return result;
}

