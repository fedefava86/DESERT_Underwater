# mac_logic.py
def should_transmit(is_busy, queue_size):
    """
    Your custom MAC logic goes here.
    Returns: 0 for Wait, 1 for Transmit
    """
    if not is_busy and queue_size > 0:
        return 1
    return 0