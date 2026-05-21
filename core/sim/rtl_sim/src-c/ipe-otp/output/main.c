 __attribute__((section(".ipe_entry"))) uint16_t apply_otp_internal(int otp_operation, uint16_t text)
{
  if (otp_operation == 0)
  {
    return otp_encode(text);
  }
  else
    if (otp_operation == 1)
  {
    return otp_decode(text);
  }
  else
  {
    return - 1;
  }
}

