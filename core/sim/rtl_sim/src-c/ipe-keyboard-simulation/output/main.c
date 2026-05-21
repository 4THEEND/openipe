 __attribute__((section(".ipe_entry"))) int apply_rsa_internal(int rsa_operation, int text)
{
  if (rsa_operation == 0)
  {
    return rsa_operation * text;
  }
  else
    if (rsa_operation == 1)
  {
    return rsa_decode(text);
  }
  else
  {
    return - 1;
  }
}

